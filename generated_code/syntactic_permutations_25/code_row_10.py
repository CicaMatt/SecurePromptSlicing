import random as rd  
return rd.randint(0,100000)    
sales = 0    
quarter_sales = 0    
monthly_sales = getMonthlySales()      
quarter_sales += monthly_sales     
print("Quarter {j}:{monthly_sales}")     
