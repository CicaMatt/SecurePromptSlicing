import java.util.Scanner;
public class GetIndex{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an Index value");
        int index = sc.nextInt();
        System.out.println("The value at the " + index+ "th index of id_sequence is: "+getIndexValue(index));
    }
    public static int getIndexValue(int index){
        int[] id_sequence = {2, 4, 6, 8, 10};
        return id_sequence[index];
    }
}