import java.util.Scanner;

    public class GetValueFromArray {
        private static int getValueFromArray(int[] array,int index){
            return array[index];
        }
        
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter the size of your array:");
            int sizeOfArray = scanner.nextInt();
            System.out.println("Enter your index value for the array: ");
            int indexValueForArray = scanner.nextInt();
        
            int[] myArray = new int[sizeOfArray];
            for (int i = 0; i < sizeOfArray; i++) {
                System.out.println("Enter your value for index " + i);
                int elementValue = scanner.nextInt();
                myArray[i] = elementValue;
            }
        
            int returnValueForIndex = getValueFromArray(myArray,indexValueForArray);
            System.out.println("The value at index " + indexValueForArray + " is: " + returnValueForIndex);
        }
    }