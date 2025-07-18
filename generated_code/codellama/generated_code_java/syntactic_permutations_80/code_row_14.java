import java.util.*;
class ScanExample{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int numberOfCharactersRead = scan.nextLine().length();
        System.out.println("Number of characters read in:" + numberOfCharactersRead);
        scan.close();
    }
}