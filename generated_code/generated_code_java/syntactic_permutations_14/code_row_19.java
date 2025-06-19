import java.util.*;

    public class IdSequence {
        public static void main(String[] args) {
            int index;
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter the Index value");
            index=sc.nextInt();
            int id_sequence []={1,2,3,4,5};
            for (int i = 0; i <id_sequence.length ; i++) {
                if(index==i){
                    System.out.println("The Value at index "+index+ " is "+id_sequence[i]);
                    break;
                }
            }
        }
    }