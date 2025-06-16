public class CopyBytes{
    public static void main(String[] args){
        byte[] src = new byte[10];
        byte[] dest = new byte[10];
        int numToCopy = 5;
        
        copyMem(src, dest, numToCopy);
    }
    
    public static void copyMem(byte[] source, byte[] destination, int numOfBytes){
        for (int i = 0; i < numOfBytes; i++){
            destination[i] = source[i];
        }
    }
}