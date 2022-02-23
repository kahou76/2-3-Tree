    // //Redistribute Left
    // void RedistributeLeft(shared_ptr& curr){
    //     // if it friend is threenode (A B): only refactoring the small part
    //     // if leaf 
    //     if(Ifleaf(curr)){
            
    //         //if the midleft is threenode
    //         if(IfThreeNode(curr->getParent()->getMiddleLeft())){
            
    //             curr->setSmallKey(curr->getParent()->getSmallKey());
    //             curr->getParent()->setSmallKey(curr->getParent()->getMiddleLeft()->getSmallKey());
    //             curr->getParent()->getMiddleLeft()->setSmallKey(curr->getParent()->getMiddleLeft()->getMiddleKey());
    //             curr->getParent()->getMiddleLeft()->setMiddleKey(nullptr);
    //         }

    //         // if not: look for parent parent help
    //         // join the bottom node with parent node
    //         // then delete parent node for internal node
    //         else{
    //             //join the left node
    //             Merge(curr);

    //         }
    //     }

    //     //not leaf but internal node
    //     //not matter parent is two or threenode, just redistribute the small key
    //     else if(curr->getSmallKey() == nullptr && curr->getLeft() != nullptr){
    //         //if right is threenode
    //         // and if parent is twonode only
    //         if(IfTwoNode(curr->getParent())){
    //             if(IfThreeNode(curr->getParent()->getMiddleLeft())){
    //             curr->setSmallKey(curr->getParent()->getSmallKey());
    //             curr->getParent()->setSmallKey(curr->getParent()->getMiddleLeft()->getSmallKey());
    //             curr->getParent()->getMiddleLeft()->setSmallKey(curr->getParent()->getMiddleLeft()->getMiddleKey());
    //             curr->getParent()->getMiddleLeft()->setMiddleKey(nullptr);

    //             //curr->setLeft(curr->getLeft());
    //             curr->setMiddleLeft(curr->getParent()->getMiddleLeft()->getLeft());
    //             curr->getParent()->getMiddleLeft()->setLeft(curr->getParent()->getMiddleLeft()->getMiddleLeft());
    //             curr->getParent()->getMiddleLeft()->setMiddleLeft(curr->getParent()->getMiddleLeft()->getRight());
    //             curr->getParent()->getMiddleLeft()->setRight(nullptr);
    //             }

    //             else{
    //                 Merge(curr);
    //             }
    //         }

            
    //     }

    // }


    // //Redistribute Right
    // void RedistributeRight(shared_ptr<Node>& curr){
    //     // if it friend is threenode (A B): only refactoring the small part
    //     // if leaf 
    //     if(Ifleaf(curr)){
    //         //if left is threenode
    //         if(IfThreeNode(curr->getParent()->getLeft())){
            
    //             curr->setSmallKey(curr->getParent()->getSmallKey());
    //             curr->getParent()->setSmallKey(curr->getParent()->getLeft()->getMiddleKey());
    //             curr->getParent()->getLeft()->setMiddleKey(nullptr);
    //         }

    //         // if not: look for parent parent help
    //         // join the bottom node with parent node
    //         // then delete parent node for internal node
    //         else{
    //             //join the left node
    //             Merge(curr);

    //         }
    //     }

    //     //not leaf but internal node
    //     //not matter parent is two or threenode, just redistribute the small key
    //     else if(curr->getSmallKey() == nullptr && curr->getLeft() != nullptr){
    //         //parent is two node only
    //         //if left is threenode
    //         if(IfThreeNode(curr->getParent()->getLeft()) && IfTwoNode(curr->getParent())){
    //             curr->setSmallKey(curr->getParent()->getSmallKey());
    //             curr->getParent()->setSmallKey(curr->getParent()->getLeft()->getMiddleKey());
    //             curr->getParent()->getLeft()->setMiddleKey(nullptr);
    //             curr->setMiddleLeft(curr->getLeft());
    //             curr->setLeft(curr->getParent()->getLeft()->getRight());
                
    //         }

    //         else{
    //             Merge(curr);
    //         }
    //     }


    // }

    // // Merge to Left node
    // void Merge(shared_ptr<Node>& curr){
    //     if(curr->getParent()->getMiddleLeft() == curr){
    //         curr->getParent()->getLeft()->setMiddleKey(curr->getParent()->getSmallKey());
    //         curr->getParent()->setSmallKey(nullptr);
              
    //     }

    //     else if(curr->getParent()->getLeft() == curr){
    //         curr->setSmallKey(curr->getParent()->getSmallKey());
    //         curr->setMiddleKey(curr->getParent()->getMiddleLeft()->getSmallKey());
    //     }

    //     curr = curr->getParent();
    //     curr->setMiddleLeft(nullptr);      
    //     //time to separate the direction:
    //     //if parent is two node
    //     if(IfTwoNode(curr->getParent())){
    //         //if curr is stored on right
    //         if(curr->getParent()->getMiddleLeft() == curr){
    //             RedistributeRight(curr);
    //         }
    //         //if curr is stored on left
    //         else if(curr->getParent()->getLeft() == curr){
    //             RedistributeLeft(curr);
    //         }
    //     }
            
    //     //if parent is three node
    //     else if(IfThreeNode(curr->getParent())){
    //         //go ahead and use Restructure
    //         Restructure(curr);
    //         //done
    //     }

    //     //If parent is nullptr, which means reaching the root aleady
    //     //Base case
    //     else if(curr->getParent() == nullptr && curr->getSmallKey() == nullptr && curr->getLeft() != nullptr){
    //         curr = curr->getLeft();
    //         curr->setParent(nullptr);
    //         root = curr;
    //     }


    //     // else if(curr->getLeft() != nullptr){
    //     //     //two situation:
    //     //     //parent twonode
    //     //     if(IfTwoNode(curr->getParent())){
    //     //         curr->getParent()->getLeft()->setMiddleKey(curr->getParent()->getSmallKey());
    //     //         curr->getParent()->getLeft()->setRight(curr->getLeft());
    //     //         curr = curr->getParent();
    //     //         curr->setMiddleLeft(nullptr);
    //     //         curr->setSmallKey(nullptr);
    //     //         RedistributeRight(curr);
    //     //     }
            
    //     //     //parent threenode
    //     //     else if(IfThreeNode(curr->getParent())){
    //     //         //two situation:
    //     //         //node is middle left
    //     //         if(curr->getParent()->getMiddleLeft() == curr){
    //     //             curr->getParent()->getLeft()->setMiddleKey(curr->getParent()->getSmallKey());
    //     //             curr->getParent()->getLeft()->setRight(curr->getLeft());
    //     //             curr = curr->getParent();
    //     //             curr->setSmallKey(curr->getMiddleKey());
    //     //             curr->setMiddleKey(nullptr);
    //     //         }
                
    //     //         //node is right
    //     //         else if(curr->getParent()->getRight() == curr){

    //     //         }
    //     //     }
            
            
            
    //     // }
    // }

    // //Merge to Right node
    // // void MergetoRight(shared_ptr<Node>& curr){
    // //     if(curr->getMiddleLeft() == nullptr){
    // //         curr->getParent()->getMiddleLeft()->setMiddleKey(curr->getParent()->getMiddleLeft()->getSmallKey());
    // //         curr->getParent()->getMiddleLeft()->setSmallKey(curr->getParent()->getSmallKey());
    // //         curr->getParent()->setSmallKey(nullptr);
    // //         curr = curr->getParent();
    // //         curr->setLeft(nullptr);
    // //         RedistributeLeft(curr);
            
    // //     }

    // //     else if(curr->getMiddleLeft() != nullptr){
    // //         curr->getParent()->getMiddleLeft()->setMiddleKey(curr->getParent()->getMiddleLeft()->getSmallKey());
    // //         curr->getParent()->getMiddleLeft()->setSmallKey(curr->getParent()->getSmallKey());

    // //         curr->getParent()->getMiddleLeft()->setRight(curr->getParent()->getMiddleLeft()->getMiddleLeft());
    // //         curr->getParent()->getMiddleLeft()->setMiddleLeft(curr->getParent()->getMiddleLeft()->getLeft());
    // //         curr->getParent()->getMiddleLeft()->setLeft(curr->getMiddleLeft());

    // //         curr = curr->getParent();
    // //         curr->setLeft(nullptr);
    // //         curr->setSmallKey(nullptr);
    // //         RedistributeLeft(curr);
    // //         //curr->getParent()->setMiddleLeft(nullptr);
    // //     }
    // // }