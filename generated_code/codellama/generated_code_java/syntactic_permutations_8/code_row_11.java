public class CmdArgs {
        
        // method to get an argument
        public static String getArgument(String[] args){
            int index = Integer.parseInt(args[0]);
            return args[index];
        }
    }