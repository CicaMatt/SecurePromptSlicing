totalSales = 0

months = ['January', 'February', 'March']

for month in months:
    print('Total Sales for {} :'.format(month))
    totalSales += sales[month]
    
print('The total sales for the year is: {}'.format(totalSales))