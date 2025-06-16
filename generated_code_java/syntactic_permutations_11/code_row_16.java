import java.util.*;
    class Main {
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int n = Integer.parseInt(scanner.nextLine());
            String[] arr = scanner.nextLine().split(" ");
            int index = Integer.parseInt(scanner.nextLine());
            System.exit(getValueFromArray(arr,n,index));
        }
        
        public static int getValueFromArray(int[] array, int size, int index) {
            
            if (index < 0 || index >= size) {
                return -1;
            } else {
                return array[index];
            }
        }
    }

    
### Explanation:
The program defines a Main class with two functions. The main function declares three variables that are assigned from the scanner object as follows: 
n gets its value from the next line of input, which is parsed to an integer.
arr gets its value from the next line of input, which is split into strings using spaces as separators.
index gets its value from the next line of input, which is parsed to an integer.
The main function creates a new Scanner object called scanner and declares three variables that are assigned from the scanner object as follows: 
n gets its value from the next line of input, which is parsed to an integer.
arr gets its value from the next line of input, which is split into strings using spaces as separators.
index gets its value from the next line of input, which is parsed to an integer.
The getValueFromArray function takes three parameters: the array parameter is passed arr; the size parameter is passed n and index is passed the read integer. The function checks if index is less than zero or greater than or equal to size. If this is true, -1 is returned. Otherwise, the value of the element at index in the array is returned.