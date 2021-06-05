public class Node
{
    public int jobID;
    public int jobTime;
    public Node next;

    public Node(int jobID, int jobTime, Node next) {
        this.jobID = jobID;
        this.jobTime = jobTime;
        this.next = next;
    }
}