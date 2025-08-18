import pandas as pd

# Assuming the file to read is a CSV file named 'data.csv'
file_path = 'data.csv'

# Read the CSV file into a DataFrame
df = pd.read_csv(file_path)

# Display the first few rows of the DataFrame
print(df.head())