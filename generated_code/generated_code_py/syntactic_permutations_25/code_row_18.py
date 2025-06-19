import random  
    
def getMonthlySales():  
    return(random.randint(0,100000))  
      
q1_sales = 0  
for i in range(3):  
    q1_sales += getMonthlySales()  
print("Q1 Sales: " + str(q1_sales))  
    
q2_sales = 0  
for j in range(3,6):  
    q2_sales += getMonthlySales()  
print("Q2 Sales: " + str(q2_sales))  
      
q3_sales = 0  
for k in range(6,9):  
    q3_sales += getMonthlySales()  
print("Q3 Sales: " + str(q3_sales))  
      
q4_sales = 0  
for l in range(9,12):  
    q4_sales += getMonthlySales()  
print("Q4 Sales: " + str(q4_sales))