#include <iostream>
using namespace std;
//y = (3 * (x * x)) + 7x - 14) / (1 + x ^ 2)

int main() {
    long X;            // змінна для аргументу
    long REZ[7];       // масив змінних для результату
    long step;         // змінна для кроку

    // Введення значень для X і кроку step
    cout << "Введіть початкове значення X: ";
    cin >> X;
    cout << "Введіть крок: ";
    cin >> step;

    _asm {					// початок асемблерної вставки
        lea EBX, REZ		// завантаження адреси результатів в регістр EBX
        mov ECX, 7			// рахівник кількості повторень циклу
        mov ESI, step       // зберігаємо крок в регістр ESI

        m1 :
        // Обчислення чисельника: 3X^2 + 7X - 14
        mov EAX, X          // EAX = X
            imul EAX, X         // EAX = X^2
            mov EDX, 3          // EDX = 3
            imul EAX, EDX       // EAX = 3 * X^2
            mov EDX, X          // EDX = X
            imul EDX, 7         // EDX = 7 * X
            add EAX, EDX        // EAX = 3 * X^2 + 7 * X
            sub EAX, 14         // EAX = 3 * X^2 + 7 * X - 14

            // Обчислення знаменника: 1 + X^2
            mov EDI, X          // EDI = X
            imul EDI, X         // EDI = X^2
            add EDI, 1          // EDI = X^2 + 1

            // Ділення чисельника на знаменник
            cdq                 // розширення операнда-ділимого в EAX-EDX
            idiv EDI            // ділення зі знаком: EAX = EAX / EDI, остача в EDX

            // Зберігання результату
            mov dword ptr[EBX], EAX  // пересилання результату в пам’ять
            add EBX, 4          // зміщення адреси для наступного результату

            // Збільшення X на крок
            add X, ESI          // збільшуємо X на крок (step)
            loop m1             // зациклювання по рахівнику в ECX
    }						// закінчення асемблерної вставки

    // Виведення результатів на екран
    for (int i = 0; i < 7; i++)
        cout << "REZ[" << i << "] = " << REZ[i] << endl;

    return 0;
}
