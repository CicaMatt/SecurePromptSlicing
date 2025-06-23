public class memcpy {
        public void copy(int destination, int source, int size){
            for(int i=0;i<size;i++){
                System.arraycopy(destination,source,size);
            }
        }
    }