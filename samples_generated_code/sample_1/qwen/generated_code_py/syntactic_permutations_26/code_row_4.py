def getMonthlySales(month):
    # Placeholder function to simulate getting monthly sales
    # In a real scenario, this function would fetch data from a database or another source
    return (month + 1) * 1000  # Example: January = 1000, February = 2000, March = 3000

sum = 0
for i in range(3):
    sum += getMonthlySales(i)

print(sum)