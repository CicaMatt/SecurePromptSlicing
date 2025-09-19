def getMonthlySales(month: int) -> float:
    # This is a placeholder function. Replace it with actual logic.
    monthly_sales = {
        0: 10000.0,  # January sales
        1: 15000.0,  # February sales
        2: 12000.0   # March sales
    }
    return monthly_sales.get(month, 0.0)

sum = 0.0

for i in range(3):
    sum += getMonthlySales(i)

print(f"Total sales for the first quarter: {sum}")