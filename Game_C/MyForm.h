#pragma once

namespace GameC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace OpenTK;
	using namespace OpenTK::Graphics;
	using namespace OpenTK::Platform::Windows;
	using namespace OpenTK::Graphics::OpenGL;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>

	struct TPO
	{
		float x;
		float y;
		float z;
	};

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: OpenTK::GLControl^ glControl1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->glControl1 = (gcnew OpenTK::GLControl());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(632, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(198, 442);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// glControl1
			// 
			this->glControl1->BackColor = System::Drawing::Color::Black;
			this->glControl1->Location = System::Drawing::Point(12, 12);
			this->glControl1->Name = L"glControl1";
			this->glControl1->Size = System::Drawing::Size(614, 442);
			this->glControl1->TabIndex = 1;
			this->glControl1->VSync = false;
			this->glControl1->Load += gcnew System::EventHandler(this, &MyForm::glControl1_Load);
			this->glControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::glControl1_MouseDown);
			this->glControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::glControl1_MouseMove);
			this->glControl1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::glControl1_MouseUp);
			this->glControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::glControl1_MouseWheel);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(842, 479);
			this->Controls->Add(this->glControl1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		GL::ClearColor(Color::SkyBlue);
		int w = glControl1->Width;
		int h = glControl1->Height;
		GL::MatrixMode(MatrixMode::Projection);
		GL::LoadIdentity();
		GL::Ortho(0,w,0,h,-1,1); // верхний угол с координатами 0,0
		GL::Viewport(0, 0, w, h); // Использовать всю поверхность GLControl под рисование

		GL::Clear(ClearBufferMask::ColorBufferBit|ClearBufferMask::DepthBufferBit);

		GL::MatrixMode(MatrixMode::Modelview);
		GL::LoadIdentity();
		GL::Color3(Color::Red);
		GL::Begin(BeginMode::Triangles);
		GL::Vertex2(10,20);
		GL::Vertex2(100, 20);
		GL::Vertex2(100, 50);
		GL::End();

		glControl1->SwapBuffers();
	}

		   // Обработка при перемещении по компоненту glControl
	private: System::Void glControl1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		Text = "Координата мыши X = " + (e->X) + "; Координата мыши Y = " + (e->Y);
		trmX = e->X;
		trmY = e->Y;

		if (md)  // если нажата мышка
		{
			trUgolX = trUgolX + (trmX - trmdX);
			trUgolY = trUgolY + (trmY - trmdY);
		}
	}

	private: System::Void glControl1_MouseWheel(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		Text = " Колесо прокрутки Delta = " + (rasto);
		if (e->Delta < 0)rasto = rasto - 1; // удаление
		if (e->Delta > 0)rasto = rasto + 1; // приближение
	}



		   const float Grad = (2 * (355/113.0)) / 360.0;

		   bool glload = false;
		   float rasto; // расстояние до объекта
		   bool md = false;
		   int trmdX=0; // координата где нажата мышка
		   int trmdY = 0;
		   int trmX = 0; // координата нахождения курсора в данный момент
		   int trmY = 0;
		   int trUgolX = 0; // угол наклона по X
		   int trUgolY=0;
		   int trUgolDX = 0; // угол наклона по X
		   int trUgolDY = 0;


	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		if (glload) // Если opengl азгружен
		{

			glControl1->Width = glControl1->Width + 1;
			glControl1->Width = glControl1->Width - 1;



			GL::ClearColor(Color::SkyBlue);
			GL::MatrixMode(MatrixMode::Projection);
			GL::LoadIdentity();
			GL::Ortho(-1, 1, -1, 1, -1, 1); // Система координат
			GL::Viewport(0, 0, glControl1->Width, glControl1->Height); // Использовать всю поверхность GLControl под рисование
			GL::Clear(ClearBufferMask::ColorBufferBit | ClearBufferMask::DepthBufferBit);

			GL::MatrixMode(MatrixMode::Projection); /// указываем матрицу
			GL::LoadIdentity(); // сброс в единичную матрицу
			Matrix4 perspective = Matrix4::CreatePerspectiveFieldOfView(0.5f, glControl1->Width / glControl1->Height, 1, 100);
			GL::LoadMatrix(perspective); // загрузка настройки протекции
			GL::ClearColor(Color::SkyBlue); // цвет фона

			TPO T[5]; // массив с точками
			for (int i = 1; i < 5; i++)
			{
				T[i].x = -0.5f; T[i].y = -0.5f; T[i].z = -10;
			}


			T[1].x = -0.5f; T[1].y = -0.5f; T[1].z = -10;
			T[2].x = -0.5f; T[2].y = 0.5f; T[2].z = -10;
			T[3].x = 0.5f; T[3].y = 0.5f; T[3].z = -10;
			T[4].x = 0.5f; T[4].y = -0.5f; T[4].z = -10;

			for (int f = 1; f < 5; f++)
			{				 
				TrUgol(T[f].y, T[f].z,trUgolY); // вверх вниз
				TrUgol(T[f].x, T[f].z, trUgolX); // влево вправо
				T[f].z = T[f].z - rasto;
			}

			GL::Color3(Color::Yellow); // цвет которым буду рисовать
			GL::Begin(BeginMode::Quads); // фигура, которой буду рисовать

			for (int f = 1; f < 5; f++)
			{
				GL::Vertex3(T[f].x, T[f].y, T[f].z); // рисую точку плоскости
			}

			GL::End();

			glControl1->SwapBuffers(); // вывожу содержимое в буфер opengl
			glControl1->Invalidate(); // перерисовка компонента на форме
		}

	}


		   // преобразование iX,iY поворачивая
		   void TrUgol(float &iX, float &iY, int iU)
		   {
			   float X,Y;
			   float U = Grad * (float)iU;
			   X = iX * Math::Cos(U) - iY * Math::Sin(U);
			   Y = iX * Math::Sin(U) + iY * Math::Cos(U);
			   iX = X;
			   iY = Y;

		   }

private: System::Void glControl1_Load(System::Object^ sender, System::EventArgs^ e) {
	glload = true;
}
private: System::Void glControl1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	md = true;
	trmdX = e->X;
	trmdY = e->Y;
	trUgolDX = trUgolX; // запоминаем углы наклона до нажатия мышки
	trUgolDY = trUgolY;
}
private: System::Void glControl1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	md = false;
}
};
}
