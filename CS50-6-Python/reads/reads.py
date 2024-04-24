# The 'reads' program is to practice reading dictionaries from a separate csv file

# There are 2 main reading methods in the csv module:
# The DictReader method reads the csv file and stores the information in a dictionary format with key value pairs (dictionary per row)
    # file_reader contains a list of all dictionaries read, each dictionary containing a "title" (key): value and "author" (key): value
        # aka each row is a dictionary of its own, with the top most row being the keys for each dictionary
    # book contains each seperate dictionary (each separate row of values linked to the key in the top most row)
# The reader method reads the csv file and stores the information as lists for each row
    # file_reader would contain all rows read (including the title/author header), each row being in a separate list
    # row would contain each separate list of information in the row

import csv

books = []

# Add books to your shelf by reading from books.csv

with open("books.csv") as file:
    file_reader = csv.DictReader(file)
    for book in file_reader:
        books.append(book)

# Print titles of books
for book in books:
    print(book["title"])
