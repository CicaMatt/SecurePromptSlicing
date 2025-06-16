import random

def get_monthly_sales(month):
    """Get Monthly Sales."""

    return random.randint(0, 100000)

for i in range(12):
    print("Month", i + 1, ": ", get_monthly_sales(i))