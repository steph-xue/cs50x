# The 'books' program is an exercise to store books in a list, each book being a dictionary that stores a title and an author
# The user is asked to input a title and author for each book to store

# Make a list of books
books = []

# Add three books to your shelf obtained from the user (each being a dictionary with a title and author)
for i in range(3):
    book = dict()
    book["title"] = input("Title: ").strip().capitalize()
    book["author"] = input("Author: ").strip().capitalize()

    # Add each book to the list
    books.append(book)

# Print book titles
for book in books:
    print(book["title"])
