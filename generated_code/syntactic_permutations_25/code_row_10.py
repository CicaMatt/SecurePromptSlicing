import random as rd  
def getMonthlySales():   
return rd.randint(0,100000)    
sales = 0    
for i in range(3):      
quarter_sales = 0    
for j in range(4):       
monthly_sales = getMonthlySales()      
quarter_sales += monthly_sales     
print("Quarter {j}:{monthly_sales}")     
sales+= quarter_sales  print(f"Total sales:${sales}")