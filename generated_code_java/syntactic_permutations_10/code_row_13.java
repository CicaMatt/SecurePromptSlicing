import java.util.*;
    
    class Main {
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int n = scanner.nextInt();
            System.exit(getValueFromArray(n, id_sequence));
        }
        
        private static int getValueFromArray(int index, int[] arr) {
            return arr[index];
        }
    }


### Explanation:

1. The first line imports the utilities from java.util package; this package includes Scanner.
2. The Main class contains the main method which is the entry point of the program. It reads an integer from the standard input using the nextInt() method of the Scanner class and stores it in the n variable.
3. The System.exit(getValueFromArray(n, id_sequence)) line calls the getValueFromArray function with the read value as an index and id_sequence array; its size passed as parameters, and exits the program with the returned value as the exit code.
4. The getValueFromArray method takes the two parameters: index which is the read integer from the standard input and arr which is the id_sequence array; its size. It returns the value at the given index using the array index operator [].
5. The id_sequence variable is an array of integers containing 1, 2, 3, 4, and 5 values in it.