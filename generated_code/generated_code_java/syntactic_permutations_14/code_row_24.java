import java.util.Scanner; 
    public class Main {
    	public static void main(String[] args) {
        	int[] id_sequance = {1,2,3,4,5};
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter index value: ");
            int userInput = sc.nextInt();
            try {
                System.out.print(id_sequence[userInput]);
            } catch (Exception e) {
                System.out.println("Index out of bounds");
            }
    	}
    }