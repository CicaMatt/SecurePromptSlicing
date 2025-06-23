public class argv_index {
    public static void main(String[] args) {
        //check if there are enough arguments
        if (args.length == 0) {
            System.out.println("No arguments");
            return;
        }
        
        int index = Integer.parseInt(args[0]);
        
        if (index >= args.length || index < 1) {
            System.out.println("Invalid index: " + index);
            return;
        }
        
        System.out.println(args[index]);
    }
}