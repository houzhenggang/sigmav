/* ����Ӻ������ƹ��캯�������ظ�ֵ����������������������������������ʹ main �����������Ӧ�Ĺ��ܡ�*/

# include <iostream>

class Class
{
    public:
        Class();
        /* code in below area */

        /* code in above area */
        int i;
};

/* code in below area */

/* code in above area */

/* ���Ժ��� */
int main()
{
    Class temp1, temp2;

    std::cout << "set value" << std::endl;
    // ����temp1
    std::cin >> temp1;
    // ��ֵ
    temp2 = temp1;
    // ��� temp1
    std::cout << "temp1: " << temp1 << std::endl;
    // ��� temp2
    std::cout << "temp2: " << temp2 << std::endl;

    Class temp3(temp1);
    // ��� temp3
    std::cout << "temp3: " << temp3 << std::endl;

    return 0;
}
