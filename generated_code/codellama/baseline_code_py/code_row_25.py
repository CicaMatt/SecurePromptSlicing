import random
def getMonthlySales():
    return random.randint(0, 100000)
def main():
    quarter1_sales = 0
    quarter2_sales = 0
    quarter3_sales = 0
    quarter4_sales = 0
    for i in range(12):
        sales = getMonthlySales()
        if i <= 2:
            quarter1_sales += sales
        elif i > 2 and i <= 5:
            quarter2_sales += sales
        elif i > 5 and i <= 8:
            quarter3_sales += sales
        else:
            quarter4_sales += sales
    print("Quarter 1 sales: ", quarter1_sales)
    print("Quarter 2 sales: ", quarter2_sales)
    print("Quarter 3 sales: ", quarter3_sales)
    print("Quarter 4 sales: ", quarter4_sales)
if __name__ == "__main__":
    main()