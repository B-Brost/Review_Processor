import openai as OpenAI
import json
# walk through your list of reviews (reviews.txt) and summarize them
def summarize_reviews(client: OpenAI, reviews) -> str:
    """
    Overall, the reviews for the Laffy Taffy candy are mixed. 
    Customers generally enjoy the taste and chewiness of the candy, 
    but there are some complaints about issues like hard texture, odd 
    odor, and inconsistent flavor distribution. Some customers were happy
    with the freshness and size of the package, while others were 
    disappointed with the quality and flavor variety they received.
    """
    # Define the prompt
    prompt = f"Summarize the reviews: {reviews}."

    # Get the LLM response
    completion = client.chat.completions.create(
        model = 'gpt-3.5-turbo',
        messages = [
            {'role' : 'system', 'content' : 'You are a review summarizer.'},
            {'role' : 'user', 'content' : prompt}
        ],
        temperature=0.6,
        max_tokens=200
    )
    
    return completion.choices[0].message.content

def infer_reviews(client: OpenAI, reviews):
    """
    "{\n    \"Texture\": [\"Fresh and chewy\", \"Hard and stale\", 
    \"Hard as rocks\"],\n    \"Taste\": [\"Yummy flavors\", \"Mango-
    passion fruit flavor not preferred\", \"Odd odor but still tasty\",
    \"No real flavor like the ones listed\"],\n    \"Price\": [\"Nice 
    size bag at a low cost\", \"Great price\"],\n    \"Distribution\": 
    [\"Unequal distribution of flavors in the bag\"],\n    \"Satisfaction
    \": [\"Enjoyed by grandkids and grown children\", \"Enjoyed despite 
    odd smell\", \"Smaller package than expected\", \"Great snack for 
    grandkids\", \"Disappointment with flavor distribution\"]\n}"
    """
    # Define the prompt
    prompt = f"Infer details from the reviews and return the inferences as a dictionary: {reviews}. For example:an inference could be on the texture, taste, or price"

    # Get the LLM response
    completion = client.chat.completions.create(
        model = 'gpt-3.5-turbo',
        messages = [
            {'role' : 'system', 'content' : 'You are a review summarizer.'},
            {'role' : 'user', 'content' : prompt}
        ],
        temperature=0.6,
        max_tokens=200
    )
    
    inferences =  completion.choices[0].message.content
    json_object = json.dumps(inferences, indent=4)
    return json_object

def HTML_table(client, reviews,inferences):
    """
    # i had to add some spaces to some of the lines to prevent errors in my code
    Here is the HTML table with the reviews, their source language, and the relevant inferences for each review:

<table>
    <tr>
    <th>Review</th>
    <th>Source Language</th>
    <th>Relevant Inferences</th>
    </tr>
    <tr>
    <td>I purchased this item to fill Easter eggs and baskets. The candy was fresh and chewy and the flavors were yummy as always. My grandkids had their first tastes and my grown children got the bulk of them in their little baskets, as these were a favorite from their childhood days. Nice size bag at a low cost and delivery was fast.</td>
    <td>English</td>
    <td>Texture: Fresh and chewy, Taste: Positive, Price: Positive</td>
    </tr>
    <tr>
    <td>These are so yummy! And a great price. I love the combinations and taste. Such a good treat
    """
    # Define the prompt
    prompt = f"""
    Given the following reviews:
    {reviews}

    And the following inferences:
    {inferences}

    Create an HTML table with all of the reviews in one column, each of them checked for the source language (put in the next column), and having the relevent inferences for each review in the third column
    """
    # Get the LLM response
    completion = client.chat.completions.create(
        model = 'gpt-3.5-turbo',
        messages = [
            {'role' : 'system', 'content' : 'You are a review summarizer and HTML table maker.'},
            {'role' : 'user', 'content' : prompt}
        ],
        temperature=0.6,
        max_tokens=200
    )
    
    return completion.choices[0].message.content

def review_email(client, reviews):
    """
    Subject: Customer Feedback on Laffy Taffy Purchase

Dear Customer Service Team,

I hope this email finds you well. I wanted to provide some feedback on my recent purchase of Laffy Taffy that I believe would be beneficial for your team to consider. Below are some key points extracted from various reviews I have come across:      

1. Positive feedback on the freshness, flavors, and cost of the candy.
2. Positive comments on the taste and price.
3. Concerns about uneven flavor distribution in the bag.
4. Mixed feedback on odor, but overall enjoyment of the candy.
5. Complaint about the hardness of the candy.
6. Disappointment with the hardness/staleness of the candy.
7. Positive feedback on freshness, but disappointment with package size.
8. Strong criticism on the hardness and lack of flavor of the candy.
9. Simple positive feedback on the snack for grandkids.
10. Disappointment with flavor distribution in the bag.

Considering these points,
    """
    #  Using the review, extract relevant information and produce an email from your agent regarding the review.
    # Define the prompt
    prompt = f"""
    Given the following reviews:
    {reviews}
    Extract relevant information and create an email from regarding the review"""
    completion = client.chat.completions.create(
        model = 'gpt-3.5-turbo',
        messages = [
            {'role' : 'system', 'content' : 'You are a review responder.'},
            {'role' : 'user', 'content' : prompt}
        ],
        temperature=0.6,
        max_tokens=200
    )
    
    return completion.choices[0].message.content

def main():
    client = OpenAI

    # Set the OpenAI API key, can also set API environment key
    // client.api_key = 'insert API Key'
    reviews = f"""
    1. I purchased this item to fill Easter eggs and baskets. The candy was fresh and chewy and the flavors were yummy as always. My grandkids had their first tastes and my grown children got the bulk of them in their little baskets, as these were a favorite from their childhood days. Nice size bag at a low cost and delivery was fast.
    2. These are so yummy! And a great price. I love the combinations and taste. Such a good treat
    3. I wasn't a huge fan of the mango-passion fruit flavor. The other combos are all really good, but a bag like this is a bit of a risk because you're not guaranteed an equal distribution of the flavors. You might get stuck with a bag where a majority of the pieces are your least favorite flavor. Still, 75% of the flavors are good, so the odds may be in your favor.
    4. Pros: Chewy, fruity goodness Cons: The bag and the candy had an odd odor to it. Didn't appear to impact the flavor so I still ate them Summary: Weird smell aside they were tasty and enjoyed
    5. I don’t know what happened but the laffy taffy was really hard to chew. So I don’t know if it had sat on a shelf for a while or what but from now on I will buy these locally.
    6. Being an adult candy lover and Laffy Taffy is one of my favorites so I was completely excited to see new flavors! I kept waiting for them ,not so patiently I have to admit. Checking daily to see if they were going to be earlier than originally expected which they were not they were right on time. I was so excited I opened the bag and eagerly unwrapped one and popped one in my mouth and they were rock hard! I nearly broke a tooth! They were stale and hard. I guess some things are better bought fresh from a store! Buyer beware
    7. The pkg. Was smaller than I thought. It was fresh and we enjoyed.
    8. These were hard as rocks! You'd break a tooth if you tried to bite one & they have no real flavor like the ones listed. Wound up throwing most of them out. I love Laffy Taffy, but not these!
    9. Great snack for grand kids
    10. We had 1 banana/berry flavor in the entire bag - which was my favorite. I am not a fan of sour, so someone else might be thrilled with most of the candy being strawberry/kiwi. We have 3 or 4 pieces of mango/passionfruit. A bit disappointing...
    """
    summary=summarize_reviews(client, reviews)
    print (summary)
    print ('\n')
    inference = infer_reviews(client, reviews)
    print (inference)
    print ('\n')
    table = HTML_table(client, reviews,inference)
    print (table)
    print ('\n')
    email = review_email(client, reviews)
    print (email)


if __name__ == "__main__":
    main()
