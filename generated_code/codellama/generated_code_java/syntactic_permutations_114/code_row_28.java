import java.util.*;
class LS{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter name of a directory or file to list :");
        String filename = sc.nextLine();
        System.out.print("\n");
        String ls = "ls" + "-l " +filename;
        System.out.println(ls);
        System.out.print("\n");
        Runtime rt = Runtime.getRuntime();
        Process proc = null;
        try{
            proc = rt.exec(ls);
        }catch(Exception e){
            e.printStackTrace();
        }
        int exitVal = 0;
        if (proc != null) {
            try {
                exitVal = proc.waitFor();
                System.out.println("\n\n Exit Value is : " + exitVal);
            } catch(Exception e){
                e.printStackTrace();
            }
        }
    }
}