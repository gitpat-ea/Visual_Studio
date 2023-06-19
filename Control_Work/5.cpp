#include <cassert>
struct JumpList { JumpList *next, *jump; unsigned id; };
void erase_jump_list(JumpList *head) {
	if (nullptr == head) return;
  erase_jump_list(head->next);
  delete head;
}

JumpList* clone_jump_list(JumpList *head){
    int counter = 0;
    JumpList *current = head;
    while(current != nullptr){
        current = current->next;
        counter++;
    }
    JumpList *new_nodes = new JumpList[counter];
    for(int i=0; i<counter; i++){
        JumpList *temp = head;
        for(int j=1; j<i; j++){
            temp = temp->next;
        }
        (new_nodes[i]).id = temp->id;
        (new_nodes[i]).next = &new_nodes[i+1];
    }
    for(int i=0; i<counter; i++){
        int number = 0;
        JumpList *tmp = head;
        for(int j = 0; j<i; j++){
            tmp = tmp->next;
        }
        JumpList *check = tmp->jump;
        while(tmp!= check){
            number++;
            tmp = tmp->next;
        }
        (new_nodes[i]).jump = &new_nodes[i+number];
    }
    return (&new_nodes[0]);
}

int main() {
  JumpList *elements = new JumpList[6];
  elements[0] = JumpList{.next = &elements[1], .jump = &elements[3], .id = 1u};
  elements[1] = JumpList{.next = &elements[2], .jump = &elements[4], .id = 2u};
  elements[2] = JumpList{.next = &elements[3], .jump = &elements[5], .id = 3u};
  elements[3] = JumpList{.next = &elements[4], .jump = &elements[5], .id = 4u};
  elements[4] = JumpList{.next = &elements[5], .jump = nullptr, .id = 5u};
  elements[5] = JumpList{.next = nullptr, .jump = nullptr, .id = 6u};
  JumpList *clone = clone_jump_list(elements);

  JumpList *a = elements, *b = clone;
  while (nullptr != a) {
    assert(a->id == b->id and a != b);
    if (nullptr != a->jump) 
      assert(a->jump->id == b->jump->id and a->jump != b->jump);
    a = a->next;
    b = b->next;
  }
  assert(nullptr == b);
  delete[] elements;
  erase_jump_list(clone);

	return 0;
}