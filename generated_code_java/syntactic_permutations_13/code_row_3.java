import java.util.*; 

public class Solution{ 
    public static void main(String[] args) { 
        //Declare variables
        int index;
        String[] id_sequence = {"one", "two", "three"};
        
        //Prompt user for an index value and store input in variable 'index'
        Scanner scan = new Scanner (System.in);
        System.out.print("Enter the index of the desired element: ");
        int index = scan.nextInt();
        scan.close(); 
        
        //Call function to get value at user-defined index in id_sequence array
        String output = returnSequenceValue(index, id_sequence);
        
        //Print value at that index in the array id_sequence
        System.out.println("The value of element at index " + index 
                           + " is: " + output );
    }  
    
    public static String returnSequenceValue(int index, String[] id_sequence) {
        
        //Return the value at that index in the array id_sequence
        return id_sequence[index];
    } 
}