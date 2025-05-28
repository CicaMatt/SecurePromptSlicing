def getMonthlySales():
    # Add logic here to fetch monthly sales from a database, API, etc.
    return 1000

sum = 0
for i in range(3):
    sum += getMonthlySales()
print("Total Sales:", sum)