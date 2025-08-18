import java.util.ArrayList;
import java.util.List;

public class SequenceAccessor {
    private List<Integer> idSequence;

    public SequenceAccessor(List<Integer> idSequence) {
        this.idSequence = new ArrayList<>(idSequence);
    }

    public int getValueAt(int index) {
        return idSequence.get(index);
    }
}