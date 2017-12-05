class node {
public:
	int val;
	node* next;
	node(int v) val(v), next(NULL) {}
};
//Q1
node* reverseLinkedList(node* head, int k) {
	if (!head || !k)
		return NULL;
	node* prev = NULL;
	node* next = NULL;
	node* curr = head;
	while (k-- > 0 && curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head->next = curr;
	head = prev;
	return head;
}
//Q2
node* reverse(node* head){
    node* curr = head;
    node* prev = NULL;
    node* next = NULL;
    while(curr){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
node* sumList(node* head1, node* head2){
    if(!head1 || !head2)
        return !head1 ? head2 : head1;
    head1 = reverse(head1);
    head2 = reverse(head2);
    int carry = 0;
    node* dummy = new node(0);
    node* move = dummy;
    while(head1 || head2){
        int sum = carry;
        carry = 0;
        if(!head1 || !head2){
            sum += !head1 ? head2->val : head1->val;
        }
        else
            sum += head1->val + head2->val;
        if(sum >= 10){
            sum -= 10;
            carry = 1;
        }
        move->next = new node(sum);
        move = move->next;
    }
    if(carry)
        move->next = new node(1);
    dummy->next = reverse(dummy->next);
    return dummy->next;
}
//Q3
//return true if there is a loop, otherwise return false;
bool checkLoop(node* head){
    if(!head)
        return false;
    node* fast = head;
    node* slow = head;
    while(fast && fast->next){
        slow = slwo->next;
        fast = fast->next->next;
        if(fast == slow)
            return true;
    }
    return false;
}
//Q4
//return true if it is a palindrome, otherwise return false;
bool isPalindrome(node* head) {
	if(!head || !head->next)
		return true;
	//get median
	node* fast = head;
	node* median = head;
	while(fast){
		if(!fast->next || !fast->next->next)
			break;
		median = median->next;
		fast = fast->next->next;
	}
	node* part2 = median->next;
	part2 = reverse(part2);
	while(part2){
		if(part2->val != head->val)
			return false;
		part2 = part2->next;
		head = head->next;
	}
	return true;
}

//Q5
node* findIntersection(node* a1, node* b1){
	//solution1: get lengths of list1 and list2
	//aolurion2: make a circle: (end) c3->next = b1, then we can find out the intersection by using Floyd's cycle-finding algorithm
	//here is the solution2
	
	//make a circle
	if(!a1 || !b1 || (!a1->next && !b1->next))
		return NULL;
	if(!a1->next)
		return a1;
	if(!b1->next)
		return b1;
	node* end = a1;
	while(end->next)
		end = end->next;
	end->next = b1;
	//Floyd's algorithm
	node* fast = a1;
	node* slow = a1;
	do{
		slow = slow->next;
		fast = fast->next->next;
	}while(slow != fast)
	fast = a1;
	while(slow != fast){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}