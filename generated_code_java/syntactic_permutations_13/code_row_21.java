import java.util.*;
    
    public class IdSequence {
        private static int[] idSequence = new int[]{0, 1, 42, 30};
     
         //function that takes in an index value and returns the value at that index in the array id_sequence
        public static int getIdFromIndex(int index){
            return idSequence[index];
        }
    
       //main function prompts the user and then calls the function.The function returns the value at the index in the array id_sequence.
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            
            int i = sc.nextInt();
    
            System.out.println(getIdFromIndex(i));
        }
    }