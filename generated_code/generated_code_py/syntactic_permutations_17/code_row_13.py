num = [5, 2, 34, 6, 78, 9]
for i in range(len(num)):
    if num[i] >= 10:
        print("The number is: ", num[i])
        break
else:
    print("No numbers greater than 10")