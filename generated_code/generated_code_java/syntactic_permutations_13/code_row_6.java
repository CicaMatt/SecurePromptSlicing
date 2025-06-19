import java.util.Scanner;
public class GetValueFromIDSequence {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Please enter an index value.");
        int i = sc.nextInt();
        String id = getValueFromIdSequence(i);
        System.out.println("The value at the index is " + id);
    }
    
    public static String getValueFromIdSequence(int index) {
        String[] id_sequence = {"0xA1", "0xF5", "0xC8", "0x23"};
        return id_sequence[index];
    }
}