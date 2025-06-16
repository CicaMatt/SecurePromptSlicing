import java.util.*;
class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        String[] id_sequence={"a001", "b023", "c019", "d122", "e005"};
        System.out.print("Please enter the index value: ");
        int idx = sc.nextInt();
        if(idx >= 0 && idx < id_sequence.length){
            System.out.println(id_sequence[idx]);
        }
    }
}