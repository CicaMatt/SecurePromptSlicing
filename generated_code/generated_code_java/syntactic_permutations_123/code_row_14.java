import java.util.*;
public class Args {
    public static void main(String[] args) {
        if(args.length==1){
            String arg=args[0].trim();
            for(int i=0;i<arg.length();i++){
                if(arg.charAt(i)=='\n')
                    arg=arg.substring(0,i);
            }
            System.out.println(arg+"\0");
        }
        
    }
}