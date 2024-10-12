#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#define COUNT 10
using namespace std;

void hienthi_menu();
void xuat_menu();

enum Color { RED, BLACK };
struct TuDien {
    string key;
    string value;
    string tuloai;  //loại từ: tính từ (adj),động từ(v),danh từ (n)
    Color color;
    TuDien* left;
    TuDien* right;
    TuDien* parent;
  
};

class RedBlackTree {
private:
    TuDien* root;
    void insertFixup(TuDien* node) {
        while (node->parent && node->parent->color == RED) 
        {
            //TH1: nút cha là con trái của ông nội
            if (node->parent == node->parent->parent->left) 
            {
                TuDien* uncle = node->parent->parent->right; // Lấy nút Uncle là con phải của ông nội

                // Case 1: Uncle là màu đỏ
                if (uncle && uncle->color == RED) 
                {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                // Case 2: Uncle là màu đen và nút hiện tại là con phải của nút cha
                else 
                {
                    if (node == node->parent->right) 
                    {
                        node = node->parent;
                        leftRotate(node);
                    }

                    // Case 3: Uncle là màu đen và nút hiện tại là con trái của nút cha
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            }

            //TH2: nút cha là con phải của ông nội
            else 
            {
                
                TuDien* uncle = node->parent->parent->left;
                // Case 1: Uncle là màu đỏ
                if (uncle && uncle->color == RED) 
                {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }

                else 
                {
                    // Case 2: Uncle là màu đen và nút hiện tại là con trái của nút cha
                    if (node == node->parent->left) 
                    {
 
                        node = node->parent;
                        rightRotate(node);
                    }

                    // Case 3: Uncle là màu đen và nút hiện tại là con phải của nút cha
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // Hàm dùng để xoay trái nút
    void leftRotate(TuDien* node) {
        TuDien* rightChild = node->right; 
        node->right = rightChild->left; 
        if (rightChild->left)
            rightChild->left->parent = node; // Cập nhật cha cho con trái của con phải của nút hiện tại
        rightChild->parent = node->parent; // Gắn cha của đỉnh quay là cha của con phải của đỉnh quay
        if (!node->parent)
            root = rightChild; // Nếu nút hiện tại là gốc, thì gán con phải của nó làm gốc mới
        else if (node == node->parent->left)
            node->parent->left = rightChild; // Nếu đỉnh quay là con trái của nút cha, thì gắn con phải của nó vào vị trí con trái của nút cha
        else
            node->parent->right = rightChild; //Ngược lại, thì gắn con phải của nó vào vị trí con phải của nút cha

        rightChild->left = node; // Gắn nút hiện tại làm con trái của con phải của nút hiện tại
        node->parent = rightChild; // Gắn con phải của nút hiện tại làm cha của nút hiện tại
        
    }

    // Hàm dùng để xoay phải nút
 void rightRotate(TuDien* node) {
        TuDien* leftChild = node->left; 
        node->left = leftChild->right; 
        if (leftChild->right)
            leftChild->right->parent = node; // Cập nhật cha cho con phải của con trái của nút hiện tại

        leftChild->parent = node->parent; // Gắn cha của đỉnh quay làm cha của con trái của nút hiện tại
        if (!node->parent)
            root = leftChild;
        else if (node == node->parent->right)
            node->parent->right = leftChild; // Nếu nút đ là con phải của nút cha, thì gắn con trái của nó vào vị trí con phải của nút cha
        else
            node->parent->left = leftChild; // ngược lại, thì gắn con trái của nó vào vị trí con trái của nút cha
        leftChild->right = node; // Gắn nút hiện tại làm con phải của con trái của nút hiện tại
        node->parent = leftChild; // Gắn con trái của nút hiện tại làm cha của nút hiện tại
    
    }

    // Hàm in đồ thị 2D của cây Red-Black Tree
    void printTree(TuDien* node, int space) {
        if (node == NULL)
            return;
        space += COUNT; // Tăng khoảng cách giữa các cấp trong đồ thị 2D

        // Đệ quy in cây bên phải
        printTree(node->right, space);
        cout << endl;
        for (int i = COUNT; i < space; i++)
            cout << " ";

        cout << node->key<<" ("<<node->tuloai<<")" << " (" << (node->color == RED ? "RED" : "BLACK") << ")" << endl;

        // Đệ quy in cây bên trái
        printTree(node->left, space);
    }


    // Hàm tìm nút kế tiếp (để thay thế khi xóa)
    TuDien* findSuccessor(TuDien* node) {
        // Lấy con phải của nút hiện tại
        TuDien* successor = node->right;

        // Duyệt xuống cùng bên trái để tìm nút lá trái nhất
        while (successor && successor->left)
            successor = successor->left;

        // Trả về nút lá trái nhất của cây con phải, là nút kế tiếp theo thứ tự của cây
        return successor;
    }
    //Tìm node dựa trên khóa
    TuDien* findNode(string key) {
        TuDien* current = root;
        while (current) 
        {
            if (key == current->key)
                return current; 
            else if (key < current->key)
                current = current->left; 
            else
                current = current->right; 
        }
        return nullptr;
    }
    void deleteFixup(TuDien* node) {
        // Lặp lại cho đến khi nút xóa là gốc hoặc màu nó là đen
        while (node != root &&(!node || node->color == BLACK)) {
            // Xử lý khi nút xóa là con trái của nút cha
            if (node == node->parent->left) {
                TuDien* sibling = node->parent->right;

                // Case 1: Xử lý khi sibling là màu đỏ
                if (sibling && sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    sibling = node->parent->right;
                }

                // Case 2: Xử lý khi cả hai con của sibling đều là màu đen
                if ((!sibling->left || sibling->left->color == BLACK) &&
                    (!sibling->right || sibling->right->color == BLACK)) {
                    sibling->color = RED;

                    // Di chuyển lên trên cây đến nút cha
                    node = node->parent;
                }
                else {
                    // Case 3: Xử lý khi con phải của sibling là màu đen
                    if (!sibling->right || sibling->right->color == BLACK) {
                        // Nếu con trái của sibling tồn tại, chuyển màu của nó thành đen
                        if (sibling->left)
                            sibling->left->color = BLACK;
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }

                    // Case 4: Xử lý khi con phải của sibling là màu đỏ
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;

                    // Nếu con phải của sibling tồn tại, chuyển màu của nó thành đen
                    if (sibling->right)
                        sibling->right->color = BLACK;
                    leftRotate(node->parent);
                    // Gán nút hiện tại là nút gốc của cây
                    node = root;
                }
            }
            else {
                // Xử lý khi nút xóa là con phải của nút cha, tương tự như trường hợp trái và phải bị đảo ngược
                TuDien* sibling = node->parent->left;

                // Case 1
                if (sibling && sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }

                // Case 2
                if ((!sibling->right || sibling->right->color == BLACK) &&
                    (!sibling->left || sibling->left->color == BLACK)) {
                    sibling->color = RED;
                    // Di chuyển lên trên cây đến nút cha
                    node = node->parent;
                }
                else {
                    // Case 3
                    if (!sibling->left || sibling->left->color == BLACK) {
                        // Nếu con phải của sibling tồn tại, chuyển màu của nó thành đen
                        if (sibling->right)
                            sibling->right->color = BLACK;
                        sibling->color = RED;
                        leftRotate(sibling);
                        // Cập nhật lại sibling
                        sibling = node->parent->left;
                    }

                    // Case 4
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->left)
                        sibling->left->color = BLACK;
                    rightRotate(node->parent);
                    // Gán nút hiện tại là nút gốc của cây
                    node = root;
                }
            }
        }
        // Đảm bảo nút gốc (nếu tồn tại) có màu đen
        if (node)
            node->color = BLACK;
    }
    // Hàm đọc dữ liệu từ file và chèn vào cây Red-Black Tree
    void readFromFile(RedBlackTree& tree, const string& filename) {
        // Mở file đầu vào
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            // Đọc từng dòng trong file
            string line;
            while (getline(inputFile, line)) {
                // Tìm vị trí khoảng trắng trong dòng để phân tách khóa và giá trị
                size_t spacePos = line.find(' ');
                size_t index = line.find('-');
                if (spacePos != string::npos) {
                    // Tách khóa và giá trị từ dòng
                    string key = line.substr(0, spacePos);
                    string value = line.substr(spacePos + 1);
                    string tu = line.substr(index+1);
                    // Chèn cặp khóa và giá trị vào cây Red-Black Tree
                    tree.insert(key,value,tu);
                }
                else {
                    // Hiển thị thông báo nếu dòng không hợp lệ (không có khoảng trắng)
                    cout << "Dong khong hop le: " << line << endl;
                }
            }
            inputFile.close();
        }
        else {
            // Hiển thị thông báo nếu không thể mở file
            cout << "Khong the mo file " << filename << " de doc." << endl;
        }
    }
    
    //Hàm lấy root
    TuDien* getRoot() const {
        return root;
    }

    // Hàm ghi dữ liệu từ cây Red-Black Tree vào file
    void writeFromFile(const RedBlackTree& tree, const string& filename) {
        // Mở file đầu ra
        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            // Gọi hàm ghi cây vào file, bắt đầu từ root
            writeTreeToFile(tree.getRoot(), outputFile);
            outputFile.close();
        }
        else {
            cout << "Khong the mo file " << filename << " de ghi." << endl;
        }
    }

    // Hàm ghi dữ liệu của cây vào file với định dạng key và value trong dấu nháy kép và cách nhau bởi khoảng trắng
    void writeTreeToFile(TuDien* node, ofstream& outputFile) {
        if (node) {
            // Gọi đệ quy để điều hướng đến nút con bên trái
            writeTreeToFile(node->left, outputFile);

            // Ghi key và value vào file với định dạng yêu cầu
            outputFile << node->key << " " << node->value<< "-" << node->tuloai << "\n";

            // Gọi đệ quy để điều hướng đến nút con bên phải
            writeTreeToFile(node->right, outputFile);
        }
    }
public:
    RedBlackTree() : root(nullptr) {}

    
        // Hàm dùng để thêm một cặp từ Anh-Việt
    void insert(string key, string value,string tuloai) { 
        TuDien* node = new TuDien{ key, value,tuloai, RED, nullptr, nullptr, nullptr }; 
        if (!root) 
        {
            root = node;
            root->color = BLACK;
        }
        else 
        {
            TuDien* current = root;
            TuDien* parent = nullptr;

            while (current) 
            {
                parent = current;
                if (key < current->key)
                    current = current->left;
                else if (key > current->key)
                    current = current->right;
                else 
                {
                    // Trường hợp từ đã tồn tại, cập nhật giá trị và giải phóng nút mới.
                    current->value = value;
                    delete node;
                    return;
                }
            }

            // Đặt con trỏ parent của nút mới trỏ đến nút cha tìm được
            node->parent = parent;

            if (key < parent->key)
                parent->left = node;
            else
                parent->right = node;
            insertFixup(node);
        }
    }
    void lietke() {
        lietKeDongTu(root);
    }
    void lietKeDongTu(TuDien* node) { // Hàm liệt kê tất cả các động từ
        if (node != NULL) {
            if (node->tuloai == "v")
                cout << node->key << "\t";
            lietKeDongTu(node->left);
            lietKeDongTu(node->right);
        }
    }
    void dem(TuDien* node,int &n1,int &n2,int &n3) { //Hàm đếm số lượng từ vựng( danh từ, động từ , tính từ)
        if (node != NULL)
        {
            dem(node->left, n1, n2, n3);
            if (node->tuloai == "v")
                n1++;
            else if (node->tuloai == "adj")
                n2++;
            else if (node->tuloai == "n")
                n3++;
            dem(node->right, n1, n2, n3);
        }
    }
    void demnode() {
        int n1 = 0, n2 = 0,n3 = 0;
        dem(root, n1, n2, n3);
        cout <<"sl dong tu="<<n1;
        cout <<"\nsl tinh tu=" << n2;
        cout <<"\nsl danh tu=" << n3;
        
    }
    TuDien* timNodeAnhEm(TuDien* node) { //Hàm tìm 1 node có ae hay không.
        if (node->parent == NULL)
            return NULL;
        else if (node == node->parent->left)
            return node->parent->right;
        else if (node== node->parent->right)
            return node->parent->left;
    }
    void timAE(string key) {
        TuDien* node;
        node = tim_node(key);
        if (node != NULL) {
            if (timNodeAnhEm(node) == NULL)
            {
                cout << "tu nay ko co ae!";
            }
            else
            {
                node = timNodeAnhEm(node);
                cout << node->key;
            }
        }
    }
    // Hàm tìm 1 node có bác hay không.
    TuDien* timNodeBac(TuDien *node) {
        if (node->parent == NULL || node->parent->parent == NULL)
            return NULL;
        else if (node->parent == node->parent->parent->left)
            return node->parent->parent->right;
        else
            return NULL;
    }
    TuDien* tim_node(string key) {
            TuDien* current = root;
            while (current)
            {
                if (key == current->key)
                    return current;
                else if (key < current->key)
                    current = current->left;
                else
                    current = current->right;
            }
            return nullptr;
        }
    
    void timBac(string key) {
        TuDien* node;
        node = tim_node(key);
        if (node != NULL) {
            if (timNodeBac(node) == NULL)
            {
                cout << "tu nay ko co bac!";
            }
            else 
            {
                node = timNodeBac(node);
                cout << node->key;
            }
        
        }
          
    }
    // Hàm dùng để tra cứu từ theo key
   string search(string key) {
        TuDien* current = root;

        // Duyệt cây để tìm kiếm từ với key tương ứng
        while (current) 
        {
            
            if (key == current->key)
                return current->value;
            else if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return "";
    }

    // Hàm tìm và xóa một nút cần xóa
    void Delete(string key) {
        // Tìm nút cần xóa dựa trên key
        TuDien* node = findNode(key);
        
        // Kiểm tra xem nút cần xóa có tồn tại không
        if (node) {
            //TH: Khi nút có cả hai con
            if (node->left!=NULL && node->right!=NULL) {
                // Tìm nút kế tiếp và thay thế giá trị của nút cần xóa bằng giá trị của nút kế tiếp
                TuDien* successor = findSuccessor(node);
                node->key = successor->key;
                node->value = successor->value;
                node->tuloai = successor->tuloai;
                // Gán nút cần xóa bằng nút kế tiếp để xóa nút kế tiếp sau này
                node = successor;
            }

            // Lấy con của nút cần xóa (nếu có)
            TuDien* child = (node->right) ? node->right : node->left;
            //TH: Khi nút có 1 con
            // Thay thế nút cần xóa bằng con của nó hoặc nullptr
            if (node->parent) {
                if (node == node->parent->left)
                    node->parent->left = child;
                else
                    node->parent->right = child;
            }
            else {
                // Nếu nút cần xóa là nút gốc, thì gán root bằng con của nó
                root = child;
                if (root)
                    root->color = BLACK; // Đảm bảo tính chất màu đen cho nút gốc
            }
            // Nếu con của nút cần xóa tồn tại, gán parent của con đó bằng parent của nút cần xóa
            if (child)
                child->parent = node->parent;
            // Nếu nút cần xóa là màu đen, cần điều chỉnh cây
            if (node->color == BLACK) {

                deleteFixup(node);
            }
            // Xóa nút cần xóa
            delete node;
        }
    }

    // Hàm sửa giá trị của một nút dựa trên key
    string remake(string key, string value) {
        TuDien* current = root;

        // Duyệt cây để tìm nút có key trùng khớp
        while (current) 
        {
            if (key == current->key) 
            {
                current->value = value;
                return current->value;
            }
            else if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return "";
    }

    // Hàm in đồ thị 2D của cây Red-Black Tree
    void print() {
        if (root) {
            printTree(root, 0);
        }
    }

    //Hàm đọc file
    void readfile(RedBlackTree& tree) {
        readFromFile(tree,"DSTuVan.txt");
    }

    //Hàm ghi file
    void writefile(RedBlackTree& tree) {
        writeFromFile(tree, "DSTuVan.txt");
    }
};

