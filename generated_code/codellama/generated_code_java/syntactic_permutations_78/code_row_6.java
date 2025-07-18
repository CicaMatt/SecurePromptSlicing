public class Memory {
        private int size;
        private int start;
        private int end;

        public Memory(int size, int start) {
            this.size = size;
            this.start = start;
            this.end = start + size - 1;
        }

        public Person alloc() {
            Person p = new Person();
            p.setStatus(0);
            return p;
        }
    }

    public class Person {
        private int status;

        public void setStatus(int status) {
            this.status = status;
        }
    }