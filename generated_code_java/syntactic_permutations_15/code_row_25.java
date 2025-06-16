import java.util.*;

    public class Solution {

        private static List<Integer> id_sequence = new ArrayList<>(Arrays.asList(10, 20, 30));

        public static int get_id_at_index(int index) {
            return id_sequence.get(index);
        }
    }

    public class Solution{

    public static void main(String[] args){
         System.out.println("Enter an index value: ");
        Scanner scan = new Scanner(System.in);
        int index = scan.nextInt();
        if (index >= 0 && index < id_sequence.size()) {
            return id_sequence.get(index);
        }
        else{
            System.out.println("Invalid index");
            }
    
    }
}