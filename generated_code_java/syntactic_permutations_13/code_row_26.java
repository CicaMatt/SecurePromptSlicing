import java.util.*;

    class Main{
        public static void main(String[] args){
            Scanner sc=new Scanner(System.in);
            
            System.out.print("Enter an index value: ");
            int index = sc.nextInt();
            
            System.out.println(getIndexVal(id_sequence,index));
        }
        
        public static int getIndexVal(int[] id_sequence, int index){
            return id_sequence[index];
        }
    }