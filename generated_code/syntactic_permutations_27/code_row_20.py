def main():
    totalSales = 0
    totalSales += get_sales('January')
    totalSales += get_sales('February')
    totalSales += get_sales('March')
    print(totalSales)