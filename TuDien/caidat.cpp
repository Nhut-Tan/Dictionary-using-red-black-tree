#include "thuvien.h"
RedBlackTree dictionary;
void hienthi_menu() {
	cout << "\n=================================================================" << endl;
	cout << "\n1. Them tu." << endl;
	cout << "\n2. Xoa tu." << endl;
	cout << "\n3. Tim tu." << endl;
	cout << "\n4. Xuat cay." << endl;
	cout << "\n5. Clear man hinh." << endl;
	cout << "\n6. Ghi file." << endl;
	cout << "\n7. Doc file." << endl;
	cout << "\n8. Liet ke dong tu." << endl;
	cout << "\n9. Dem so luong tu vung." << endl;
	cout << "\n10. Tim node bac." << endl;
	cout << "\n11. Tim node ae." << endl;
	cout << "\n0. Thoat chuong trinh." << endl;
	cout << "\n=================================================================" << endl;
}
void xuat_menu() {
	int c;
	do {
		cout << "\nNhap 1 so nguyen de lua chon chuc nang: ";
		cin >> c;
		string word;
		string trans;
		string tu;
		switch (c) {
		case 1:
			cout << "Nhap tu tieng anh can them: ";
			cin.ignore();
			getline(cin,word);
			cout << "\nNhap nghia cua tu: ";
			getline(cin, trans);
			int n;
			do
			{
				cout << "\n1.danhtu(n)";
				cout << "\n2.tinhtu(adj)";
				cout << "\n3.dongtu(v)" << endl;
				cout << "\nnhap tu loai: ";
				cin >> n;
				if (n == 1)
					tu = "n";
				else if (n == 2)
					tu = "adj";
				else if (n == 3)
					tu = "v";
			} while (n <=0 ||n>=4);

			dictionary.insert(word, trans,tu);		
			hienthi_menu();
			break;
		case 2:
			cout << "\nNhap tu ma can xoa: ";
			cin.ignore();
			getline(cin, word);
			dictionary.Delete(word);
			hienthi_menu();
			break;
		case 3:
			cout << "\nNhap tu can tra cuu: ";
			cin.ignore();
			getline(cin, word);
			trans = dictionary.search(word);
			if (trans != "")
				cout << "Nghia cua tu '" << word << "' la: " << trans << endl;
			else
				cout << "Khong tim thay tu '" << word << "' trong tu dien." << endl;
			hienthi_menu();
			break;
		case 4:
			dictionary.print();
			hienthi_menu();
			break;
		case 5:
			system("cls");
			hienthi_menu();
			break;
		case 6:
			dictionary.writefile(dictionary);
			hienthi_menu();
			break;
		case 7:
			dictionary.readfile(dictionary);
			hienthi_menu();
			break;
		case 8:
			dictionary.lietke();
			break;
		case 9:
			dictionary.demnode();
			break;
		case 10:
			cout << "nhap tu can tim:";
			cin.ignore();
			getline(cin, word);
			if (dictionary.search(word) != "") {
				cout << "tu co bac la: ";
				dictionary.timBac(word);
				cout << endl;
			}
			else
				cout << "khong co tu nay" << endl;
			hienthi_menu();
			break;
		case 11:
			cout << "nhap tu can tim:";
			cin.ignore();
			getline(cin, word);
			if (dictionary.search(word) != "") {
				cout << "tu co ae la: ";
				dictionary.timAE(word);
				cout << endl;
			}
			else
				cout << "khong co tu nay" << endl;
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	} while (c < 0||c>=0);
}