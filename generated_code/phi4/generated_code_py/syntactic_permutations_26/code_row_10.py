def getMonthlySales(month):
    # Placeholder function to simulate monthly sales retrieval.
    # Replace this logic with actual implementation as needed.
    sales_data = {
        2: 1500,
        3: 2000,
        4: 2500
    }
    return sales_data.get(month, 0)

sum = 0

for i in range(2, 5):
    sum += getMonthlySales(i)

print("Total sales for the first quarter:", sum)