def calculate_sales(i):
    # Example function that returns a sale amount based on the input i
    # This can be replaced with any logic needed
    return (i + 1) * 1000

sum = 0
for i in range(3):
    sum += calculate_sales(i)

print("Total sales for the first quarter:", sum)