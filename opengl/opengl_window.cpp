#include "opengl_window.h"
#include "appsettings.hpp"

opengl_window::opengl_window()
{
    // Стартовая настройка шрифтов
    font          = QFont("Times New Roman", 20);
    font_selected = QFont("Times New Roman", 25);
    font_selected.setBold(true);

    initialize_page_data();

    // Заполнение переменной состояния
    STATE_LIST.resize(5);
    STATE_LIST[0] = true;
    STATE_LIST[1] = false;
    STATE_LIST[2] = false;
    STATE_LIST[3] = false;

    state_list.resize(5);
    state_list[0].resize(P_1);
    state_list[1].resize(P_2);
    state_list[2].resize(P_3);
    state_list[3].resize(P_4);
    state_list[4].resize(1);

    state_list[0][0] = true;
    state_list[0][1] = false;
    state_list[0][2] = false;

    state_list[1][0] = true;
    state_list[1][1] = false;
    state_list[1][2] = false;

    state_list[2][0] = true;
    state_list[2][1] = false;

    state_list[3][0] = true;
    state_list[3][1] = false;
    state_list[3][2] = false;
    state_list[3][3] = false;

    // Создание векторов текущих настроек
    page1.vector_page_settings.resize(P_1);
    page2.vector_page_settings.resize(P_2);
    page3.vector_page_settings.resize(P_3);
    page4.vector_page_settings.resize(P_4);

    load();

    vector_total.append(page1);
    vector_total.append(page2);
    vector_total.append(page3);
    vector_total.append(page4);
}

// Далее - 3 стандартные функции OpenGL для отрисовки окна
void opengl_window::initializeGL()
{
  static auto w = appSettings::properties().screenWidth();
  static auto h = appSettings::properties().screenHeight();
  glOrtho(0, w, h, 0, 0, 1);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
}

void opengl_window::resizeGL(int aW, int aH)
{
  static auto w = appSettings::properties().screenWidth();
  static auto h = appSettings::properties().screenHeight();

  glLoadIdentity();
  glViewport(0, 0, (GLint)aW, (GLint)aH);
  glOrtho(0, w, h, 0, 0, 1);
}

void opengl_window::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  qglClearColor(Qt::darkCyan);

  draw_start_process_pages();
}

// Функция управления окном через клавиши
void opengl_window::keyReleaseEvent(QKeyEvent *apKeyEvent)
{
    // клавиши Up и Down перемещают указатель строки вверх или вниз
    if(apKeyEvent->key() == Qt::Key_Up)
    {
        for (int i=0; i < STATE_LIST.size(); i++)
            if (STATE_LIST[i])
            {
                for (int k=0; k < state_list[i].size(); k++)
                {
                    if (state_list[i][k])
                    {
                        state_list[i][k] = false;
                        if (k == 0)
                            state_list[i][state_list[i].size() - 1] = true;
                        else state_list[i][k-1] = true;
                        break;
                    }
                }
                break;
            }
    }
    if(apKeyEvent->key() == Qt::Key_Down)

    {
        for (int i=0; i < STATE_LIST.size(); i++)
            if (STATE_LIST[i])
            {
                for (int k=0; k < state_list[i].size(); k++)
                {
                    if (state_list[i][k])
                    {
                        state_list[i][k] = false;
                        if (k == (state_list[i].size()-1))
                            state_list[i][0] = true;
                        else state_list[i][k+1] = true;
                        break;
                    }
                }
                break;
            }
    }
    // 2 клавиши Enter перелистывают страницы
    if((apKeyEvent->key() == Qt::Key_Enter) || (apKeyEvent->key() == Qt::Key_Return))
    {
        for (int i=0; i < STATE_LIST.size(); i++)
            if (STATE_LIST[i])
            {
                STATE_LIST[i] = false;
                if (i+1 == STATE_LIST.size())
                    STATE_LIST[0] = true;
                else STATE_LIST[i+1] = true;
                break;
            }
    }
    // клавиши Left и Right осуществляют изменение состояния данного параметра
    if(apKeyEvent->key() == Qt::Key_Left)
    {
        for (int i=0; i < STATE_LIST.size(); i++)
            if (STATE_LIST[i])
                for (int k=0; k < state_list[i].size(); k++)
                    if(state_list[i][k])
                        for (int var=0; var<vector_total[i].vector_page_value[k].size(); var++)
                            if(vector_total[i].vector_page_settings[k] == vector_total[i].vector_page_value[k][var])
                            {
                                if (var != 0)
                                    vector_total[i].vector_page_settings[k] = vector_total[i].vector_page_value[k][var-1];
                                else vector_total[i].vector_page_settings[k] = vector_total[i].vector_page_value[k][vector_total[i].vector_page_value[k].size() - 1];
                                break;
                            }
    }
    if(apKeyEvent->key() == Qt::Key_Right)
    {
        for (int i=0; i < STATE_LIST.size(); i++)
            if (STATE_LIST[i])
                for (int k=0; k < state_list[i].size(); k++)
                    if(state_list[i][k])
                        for (int var=0; var<vector_total[i].vector_page_value[k].size(); var++)
                            if(vector_total[i].vector_page_settings[k] == vector_total[i].vector_page_value[k][var])
                            {
                                if (var != (vector_total[i].vector_page_value[k].size() - 1))
                                    vector_total[i].vector_page_settings[k] = vector_total[i].vector_page_value[k][var+1];
                                else vector_total[i].vector_page_settings[k] = vector_total[i].vector_page_value[k][0];
                                break;
                            }
    }
    // Функция updateGL() - стандартная: обновляет отрисовку окна
    updateGL();
    // Функция закрытия окна с сохранением измененных параметров
    if(apKeyEvent->key() == Qt::Key_Escape)
    {
        save();
        close();
    }
}

void opengl_window::initialize_page_data()
{
    // Заполнение полей настроек
    // Page 1
    page1.vector_page_key.resize(P_1);
    page1.vector_page_key[0] = "Вкл/Выкл";
    page1.vector_page_key[1] = "Формат";
    page1.vector_page_key[2] = "Сжатие";

    page1.vector_page_value.resize(P_1);

    page1.vector_page_value[0].resize(2);
    page1.vector_page_value[0][0] = "Вкл";
    page1.vector_page_value[0][1] = "Выкл";

    page1.vector_page_value[1].resize(2);
    page1.vector_page_value[1][0] = "Цветной";
    page1.vector_page_value[1][1] = "Черно-белый";

    page1.vector_page_value[2].resize(3);
    page1.vector_page_value[2][0] = "0%";
    page1.vector_page_value[2][1] = "30%";
    page1.vector_page_value[2][2] = "50%";

    // Page 2
    page2.vector_page_key.resize(P_2);
    page2.vector_page_key[0] = "Вкл/Выкл";
    page2.vector_page_key[1] = "Формат";
    page2.vector_page_key[2] = "Сжатие";

    page2.vector_page_value.resize(P_2);

    page2.vector_page_value[0].resize(2);
    page2.vector_page_value[0][0] = "Вкл";
    page2.vector_page_value[0][1] = "Выкл";

    page2.vector_page_value[1].resize(2);
    page2.vector_page_value[1][0] = "Цветной";
    page2.vector_page_value[1][1] = "Черно-белый";

    page2.vector_page_value[2].resize(3);
    page2.vector_page_value[2][0] = "0%";
    page2.vector_page_value[2][1] = "30%";
    page2.vector_page_value[2][2] = "50%";

    // Page 3
    page3.vector_page_key.resize(P_3);
    page3.vector_page_key[0] = "Вкл/Выкл";
    page3.vector_page_key[1] = "Диапазон";

    page3.vector_page_value.resize(P_3);

    page3.vector_page_value[0].resize(2);
    page3.vector_page_value[0][0] = "Вкл";
    page3.vector_page_value[0][1] = "Выкл";

    page3.vector_page_value[1].resize(3);
    page3.vector_page_value[1][0] = "0.01-0.05 МэВ";
    page3.vector_page_value[1][1] = "0.05-0.1 МэВ";
    page3.vector_page_value[1][2] = ">0.1 МэВ";

    // Page 4
    page4.vector_page_key.resize(P_4);
    page4.vector_page_key[0] = "Вкл/Выкл";
    page4.vector_page_key[1] = "Диапазон";
    page4.vector_page_key[2] = "Приближение";
    page4.vector_page_key[3] = "Угол";

    page4.vector_page_value.resize(P_4);

    page4.vector_page_value[0].resize(2);
    page4.vector_page_value[0][0] = "Вкл";
    page4.vector_page_value[0][1] = "Выкл";

    page4.vector_page_value[1].resize(3);
    page4.vector_page_value[1][0] = "0.01-0.05 МэВ";
    page4.vector_page_value[1][1] = "0.05-0.1 МэВ";
    page4.vector_page_value[1][2] = ">0.1 МэВ";

    page4.vector_page_value[2].resize(3);
    page4.vector_page_value[2][0] = "Нет";
    page4.vector_page_value[2][1] = "х2";
    page4.vector_page_value[2][2] = "х4";

    page4.vector_page_value[3].resize(3);
    page4.vector_page_value[3][0] = "0";
    page4.vector_page_value[3][1] = "15";
    page4.vector_page_value[3][2] = "30";
}

void opengl_window::draw_start_process_pages()
{
    if (STATE_LIST[0])
        process_page1();
    else if (STATE_LIST[1])
        process_page2();
    else if (STATE_LIST[2])
        process_page3();
    else if (STATE_LIST[3])
        process_page4();
    else if (STATE_LIST[4])
        process_page5();
}

void opengl_window::process_page1()
{
    x = 20;
    y = 30;

    qglColor(Qt::gray);
    renderText(x, y, "Page 1", font);
    qglColor(Qt::yellow);
    renderText(mid_width, y + dy, "Камера Ximea №1", font_selected);
    y = y + 2*dy;

    for(int i = 0; i < state_list[0].size(); i++)
    {
      if(state_list[0][i])
      {
        qglColor(Qt::red);
        renderText(x, y, vector_total[0].vector_page_key[i], font_selected);
        renderText(x+350, y, vector_total[0].vector_page_settings[i], font_selected);
      }
      else
      {
        qglColor(Qt::white);
        renderText(x, y, vector_total[0].vector_page_key[i], font);
        renderText(x+350, y, vector_total[0].vector_page_settings[i], font);
      }
      y += dy;
    }
}

void opengl_window::process_page2()
{
    x = 20;
    y = 30;

    qglColor(Qt::gray);
    renderText(x, y, "Page 2", font);
    qglColor(Qt::yellow);
    renderText(mid_width, y + dy, "Камера Ximea №2", font_selected);
    y = y + 2*dy;

    for(int i = 0; i < state_list[1].size(); i++)
    {
      if(state_list[1][i])
      {
        qglColor(Qt::red);
        renderText(x, y, vector_total[1].vector_page_key[i], font_selected);
        renderText(x+350, y, vector_total[1].vector_page_settings[i], font_selected);
      }
      else
      {
        qglColor(Qt::white);
        renderText(x, y, vector_total[1].vector_page_key[i], font);
        renderText(x+350, y, vector_total[1].vector_page_settings[i], font);
      }
      y += dy;
    }
}

void opengl_window::process_page3()
{
    x = 20;
    y = 30;

    qglColor(Qt::gray);
    renderText(x, y, "Page 3", font);
    qglColor(Qt::yellow);
    renderText(mid_width, y + dy, "Спектрометр", font_selected);
    y = y + 2*dy;

    for(int i = 0; i < state_list[2].size(); i++)
    {
      if(state_list[2][i])
      {
        qglColor(Qt::red);
        renderText(x, y, vector_total[2].vector_page_key[i], font_selected);
        renderText(x+350, y, vector_total[2].vector_page_settings[i], font_selected);
      }
      else
      {
        qglColor(Qt::white);
        renderText(x, y, vector_total[2].vector_page_key[i], font);
        renderText(x+350, y, vector_total[2].vector_page_settings[i], font);
      }
      y += dy;
    }
}

void opengl_window::process_page4()
{
    x = 20;
    y = 30;

    qglColor(Qt::gray);
    renderText(x, y, "Page 4", font);
    qglColor(Qt::yellow);
    renderText(mid_width, y + dy, "Гамма-локатор", font_selected);
    y = y + 2*dy;

    for(int i = 0; i < state_list[3].size(); i++)
    {
      if(state_list[3][i])
      {
        qglColor(Qt::red);
        renderText(x, y, vector_total[3].vector_page_key[i], font_selected);
        renderText(x+350, y, vector_total[3].vector_page_settings[i], font_selected);
      }
      else
      {
        qglColor(Qt::white);
        renderText(x, y, vector_total[3].vector_page_key[i], font);
        renderText(x+350, y, vector_total[3].vector_page_settings[i], font);
      }
      y += dy;
    }
}

void opengl_window::process_page5()
{
    x = 20;
    y = 30;

    qglColor(Qt::gray);
    renderText(x, y, "Page 5", font);
    y += 40;

    if(Image.empty())
        qDebug() << "Image is unavailable. Connect camera";
    else
    {
        cv::flip(Image, Image, 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(1, &Texture1);
        glBindTexture(GL_TEXTURE_2D, Texture1);

        GLint internalformat = GL_RGB32F;
        if (Image.channels() == 4) internalformat = GL_RGBA;
        if (Image.channels() == 3) internalformat = GL_RGB;
        if (Image.channels() == 2) internalformat = GL_RG;
        if (Image.channels() == 1) internalformat = GL_RED;

        GLenum externalformat = GL_RGB;
        if (Image.channels() == 1)
            externalformat = GL_RED; // GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT32F, GL_R32F NOT WORKING!

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, internalformat, Image.cols, Image.rows, 0, externalformat, GL_UNSIGNED_BYTE, Image.ptr());
        drawTexture(QRect{x, y, x+740, y+440}, Texture1);
    }
}

void opengl_window::TakePicture1(Mat InputImage)
{
    Image = InputImage;
    cvtColor(Image,Image,COLOR_RGBA2RGB);
    //qDebug() << Image.depth() << Image.channels() << Image.type();
}

void opengl_window::load()
{
    QFile file("settings.txt");
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray ar;
            for (int i=0; i<page1.vector_page_settings.size(); i++)
            {
                ar = file.readLine();
                page1.vector_page_settings[i] = QString(ar);
                page1.vector_page_settings[i].chop(1);
            }
            for (int k=0; k<page2.vector_page_settings.size(); k++)
            {
                ar = file.readLine();
                page2.vector_page_settings[k] = QString(ar);
                page2.vector_page_settings[k].chop(1);
            }
            for (int j=0; j<page3.vector_page_settings.size(); j++)
            {
                ar = file.readLine();
                page3.vector_page_settings[j] = QString(ar);
                page3.vector_page_settings[j].chop(1);
            }
            for (int r=0; r<page4.vector_page_settings.size(); r++)
            {
                ar = file.readLine();
                page4.vector_page_settings[r] = QString(ar);
                page4.vector_page_settings[r].chop(1);
            }

            file.close();
        }
        else qDebug() << "File open error!";
    }
    else
    {
        for (int i=0; i<page1.vector_page_settings.size(); i++)
            page1.vector_page_settings[i] = page1.vector_page_value[i][0];
        for (int k=0; k<page2.vector_page_settings.size(); k++)
            page2.vector_page_settings[k] = page2.vector_page_value[k][0];
        for (int j=0; j<page3.vector_page_settings.size(); j++)
            page3.vector_page_settings[j] = page3.vector_page_value[j][0];
        for (int r=0; r<page4.vector_page_settings.size(); r++)
            page4.vector_page_settings[r] = page4.vector_page_value[r][0];
    }
}

void opengl_window::save()
{
    QFile file("settings.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        for (int i=0; i<page1.vector_page_settings.size(); i++)
        {
            file.write(vector_total[0].vector_page_settings[i].toStdString().c_str());
            file.write("\n");
        }
        for (int k=0; k<page2.vector_page_settings.size(); k++)
        {
            file.write(vector_total[1].vector_page_settings[k].toStdString().c_str());
            file.write("\n");
        }
        for (int j=0; j<page3.vector_page_settings.size(); j++)
        {
            file.write(vector_total[2].vector_page_settings[j].toStdString().c_str());
            file.write("\n");
        }
        for (int r=0; r<page4.vector_page_settings.size(); r++)
        {
            file.write(vector_total[3].vector_page_settings[r].toStdString().c_str());
            file.write("\n");
        }
        file.close();
    }
    else qDebug() << "Save data error!";
}

