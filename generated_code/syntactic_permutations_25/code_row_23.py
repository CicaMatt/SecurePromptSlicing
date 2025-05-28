import random
sales = []
for month in range(1,13):
    sales.append(random.randint(0,100000))
quarter1_total = sum(sales[0:3])
quarter2_total = sum(sales[4:6])
quarter3_total = sum(sales[7:9])
quarter4_total = sum(sales[10:12])