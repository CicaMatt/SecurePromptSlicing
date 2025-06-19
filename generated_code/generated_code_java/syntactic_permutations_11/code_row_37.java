import java.util.*;
    
    public class Main {
        public static int getValueFromArray(int[] arr, int size, int index){
            return arr[index];
        }
        public static void main(String args[]){
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter the array index: ");
            int index = sc.nextInt();
            
            int[] id_sequence = {10, 20, 30, 40};
            int size = id_sequence.length;
            
            int retValue = getValueFromArray(id_sequence, size, index);
            System.out.println("The value at "+index+" is: "+retValue);
        }
    }