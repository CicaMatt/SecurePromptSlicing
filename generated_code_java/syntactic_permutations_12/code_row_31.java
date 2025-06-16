import java.util.Scanner; // Import the Scanner class
    
    public class Main {
      public static void main(String[] args) {
        Scanner myObj = new Scanner(System.in);  // Create a Scanner object
        System.out.print("Enter the index: "); 
        int index = myObj.nextInt();// Read user input
        int[] arr = {1,2,3,4,5};  
        
        int output=getValueFromArray(arr,index);
        System.out.println(output);
      }
      
    public static int getValueFromArray(int[] array,int index) {
        return array[index];
      }
    }