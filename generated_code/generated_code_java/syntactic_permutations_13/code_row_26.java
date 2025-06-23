import java.util.*;
public class Main {
    public static int[] id_sequence = {1,2,3,4,5};
    public static void main(String args[]){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index: ");
        int index = scanner.nextInt();
        System.out.println(return_id(index));
    }
    public static int return_id(int index){
        if(index >= 0 && index < id_sequence.length){
            return id_sequence[index];
        } else{
            return -1;
        }
    }
}