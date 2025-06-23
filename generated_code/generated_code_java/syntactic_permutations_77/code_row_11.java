import java.util.*;
    
    public class Person {
        private String name;
        private int status;
        
        public Person() {}
        
        public Person(String name, int status) {
            this.name = name;
            this.status = status;
        }
        
        public void setName(String name) {
            this.name = name;
        }
        
        public String getName() {
            return name;
        }
        
        public void setStatus(int status) {
            this.status = status;
        }
        
        public int getStatus() {
            return status;
        }
    }
    
    public class MemoryAllocator {
        private static final int BLOCK_SIZE = 64 * 1024; // 64Kb
        private static final int HEADER_SIZE = 8; // 8 bytes
        
        private byte[] memoryBlock;
        
        public MemoryAllocator(int blockSize) {
            memoryBlock = new byte[blockSize];
        }
        
        public byte[] allocate(int size) {
            if (size > BLOCK_SIZE - HEADER_SIZE) {
                return null;
            }
            
            for (int i = 0; i < memoryBlock.length; i++) {
                if (memoryBlock[i] == 0) {
                    memoryBlock[i] = 1;
                    
                    // set header
                    int headerValue = size + HEADER_SIZE;
                    for (int j = 0; j < HEADER_SIZE; j++) {
                        memoryBlock[i + j] = (byte) ((headerValue >> (j * 8)) & 0xFF);
                    }
                    
                    // set body
                    for (int j = 0; j < size; j++) {
                        memoryBlock[i + HEADER_SIZE + j] = 0;
                    }
                    
                    return Arrays.copyOfRange(memoryBlock, i + HEADER_SIZE, i + HEADER_SIZE + size);
                }
            }
            
            return null;
        }
        
        public void free(byte[] memory) {
            int startIndex = getStartIndex(memory);
            if (startIndex == -1) {
                throw new IllegalArgumentException("Invalid memory");
            }
            
            for (int i = 0; i < HEADER_SIZE + getSize(memory); i++) {
                memoryBlock[startIndex + i] = 0;
            }
        }
        
        private int getStartIndex(byte[] memory) {
            if (memory == null || memory.length == 0) {
                return -1;
            }
            
            for (int i = 0; i < memoryBlock.length; i++) {
                if (memoryBlock[i] == 1 && memoryBlock[i + HEADER_SIZE] == memory[0]) {
                    return i;
                }
            }
            
            return -1;
        }
        
        private int getSize(byte[] memory) {
            if (memory == null || memory.length == 0) {
                throw new IllegalArgumentException("Invalid memory");
            }
            
            int size = 0;
            for (int i = HEADER_SIZE - 1; i >= 0; i--) {
                size += (memory[i] & 0xFF) << (8 * i);
            }
            
            return size - HEADER_SIZE;
        }
    }
    
    public class Driver {
        
        public static void main(String[] args) {
            MemoryAllocator allocator = new MemoryAllocator(1024);
            Person person = (Person)allocator.allocate(8); // should return the first 8 bytes of memoryBlock
            
            if (person != null) {
                person.setStatus(0);
                person.setName("John");
            }
        }
    }