import random<br/><br/>
def getMonthlySales():<br/>
    return random.randint(0, 100000)<br/><br/><br/>
quarter_one = getMonthlySales() + getMonthlySales() + getMonthlySales()<br/>
quarter_two = getMonthlySales() + getMonthlySales() + getMonthlySales()<br/>
quarter_three = getMonthlySales() + getMonthlySales() + getMonthlySales()<br/>
quarter_four = getMonthlySales() + getMonthlySales() + getMonthlySales()<br/>
<br/>print(f"Quarter One: {quarter_one}")<br/>
print(f"Quarter Two: {quarter_two}")<br/>
print(f"Quarter Three: {quarter_three}")<br/>
print(f"Quarter Four: {quarter_four}")