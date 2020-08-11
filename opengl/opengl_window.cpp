#include "opengl_window.h"
#include "appsettings.hpp"

opengl_window::opengl_window()
{
    // Стартовая настройка шрифтов
    font          = QFont("Times New Roman", 20);
    font_selected = QFont("Times New Roman", 25);
    font_selected.setBold(true);

    // Заполнение полей настроек
    // Page 1
    page1.vector_page_key.resize(3);
    page1.vector_page_key[0] = "Вкл/Выкл";
    page1.vector_page_key[1] = "Формат";
    page1.vector_page_key[2] = "Сжатие";

    page1.vector_page_value.resize(3);

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
    page2.vector_page_key.resize(3);
    page2.vector_page_key[0] = "Вкл/Выкл";
    page2.vector_page_key[1] = "Формат";
    page2.vector_page_key[2] = "Сжатие";

    page2.vector_page_value.resize(3);

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
    page3.vector_page_key.resize(2);
    page3.vector_page_key[0] = "Вкл/Выкл";
    page3.vector_page_key[1] = "Диапазон";

    page3.vector_page_value.resize(2);

    page3.vector_page_value[0].resize(2);
    page3.vector_page_value[0][0] = "Вкл";
    page3.vector_page_value[0][1] = "Выкл";

    page3.vector_page_value[1].resize(3);
    page3.vector_page_value[1][0] = "0.01-0.05 МэВ";
    page3.vector_page_value[1][1] = "0.05-0.1 МэВ";
    page3.vector_page_value[1][2] = ">0.1 МэВ";

    // Page 4
    page4.vector_page_key.resize(4);
    page4.vector_page_key[0] = "Вкл/Выкл";
    page4.vector_page_key[1] = "Диапазон";
    page4.vector_page_key[2] = "Приближение";
    page4.vector_page_key[3] = "Угол";

    page4.vector_page_value.resize(4);

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

    // Заполнение переменной состояния
    STATE_LIST.resize(4);
    STATE_LIST[0] = true;
    STATE_LIST[1] = false;
    STATE_LIST[2] = false;
    STATE_LIST[3] = false;

    state_list.resize(4);
    state_list[0].resize(3);
    state_list[0][0] = true;
    state_list[0][1] = false;
    state_list[0][2] = false;

    state_list[1].resize(3);
    state_list[1][0] = true;
    state_list[1][1] = false;
    state_list[1][2] = false;

    state_list[2].resize(2);
    state_list[2][0] = true;
    state_list[2][1] = false;

    state_list[3].resize(4);
    state_list[3][0] = true;
    state_list[3][1] = false;
    state_list[3][2] = false;
    state_list[3][3] = false;

    // Создание вектора текущих настроек

    //--------------------------
    page1.vector_page_settings.resize(3);
    page1.vector_page_settings[0] = page1.vector_page_value[0][0];
    page1.vector_page_settings[1] = page1.vector_page_value[1][0];
    page1.vector_page_settings[2] = page1.vector_page_value[2][0];

    page2.vector_page_settings.resize(3);
    page2.vector_page_settings[0] = page2.vector_page_value[0][0];
    page2.vector_page_settings[1] = page2.vector_page_value[1][0];
    page2.vector_page_settings[2] = page2.vector_page_value[2][0];

    page3.vector_page_settings.resize(2);
    page3.vector_page_settings[0] = page3.vector_page_value[0][0];
    page3.vector_page_settings[1] = page3.vector_page_value[1][0];

    page4.vector_page_settings.resize(4);
    page4.vector_page_settings[0] = page4.vector_page_value[0][0];
    page4.vector_page_settings[1] = page4.vector_page_value[1][0];
    page4.vector_page_settings[2] = page4.vector_page_value[2][0];
    page4.vector_page_settings[3] = page4.vector_page_value[3][0];
    //--------------------------
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
  //glEnable(GL_TEXTURE_2D);
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
        close();
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

void opengl_window::load(QVector<QString> vector_data)
{

}

void opengl_window::save(QVector<QString> vector_data)
{

}