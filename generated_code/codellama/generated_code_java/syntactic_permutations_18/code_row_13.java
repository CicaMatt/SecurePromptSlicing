public int getValueAt(int[] myList, int index) {
        // Check if index is within bounds
        if (index < 0 || index >= myList.length) {
            throw new IndexOutOfBoundsException("Invalid index");
        }

        return myList[index];
    }