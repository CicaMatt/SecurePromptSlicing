import java.util.Scanner;
    public class GeneratedSequence {
        static int[] id_sequence = new int[]{4, 7, 23, 12};
        
        public static void main(String args[]){
            Scanner sc=new Scanner(System.in);
            System.out.println("Enter the index number");
            int idx=sc.nextInt();
            int value=returnValueAt(idx-1);
            System.out.println(value);
        }
        
        public static int returnValueAt(int index){
            return id_sequence[index];
        }
    }