// Copyright 2015 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include <QIcon>

#include "DolphinQt2/Settings.h"
#include "DolphinQt2/ToolBar.h"

static QSize ICON_SIZE(32, 32);

ToolBar::ToolBar(QWidget* parent) : QToolBar(parent)
{
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  setMovable(false);
  setFloatable(false);
  setIconSize(ICON_SIZE);

  MakeActions();
  UpdateIcons();

  EmulationStopped();
}

void ToolBar::EmulationStarted()
{
  m_play_action->setEnabled(false);
  m_play_action->setVisible(false);
  m_pause_action->setEnabled(true);
  m_pause_action->setVisible(true);
  m_stop_action->setEnabled(true);
  m_stop_action->setVisible(true);
  m_fullscreen_action->setEnabled(true);
  m_screenshot_action->setEnabled(true);
}

void ToolBar::EmulationPaused()
{
  m_play_action->setEnabled(true);
  m_play_action->setVisible(true);
  m_pause_action->setEnabled(false);
  m_pause_action->setVisible(false);
  m_stop_action->setEnabled(true);
  m_stop_action->setVisible(true);
}

void ToolBar::EmulationStopped()
{
  m_play_action->setEnabled(true);
  m_play_action->setVisible(true);
  m_pause_action->setEnabled(false);
  m_pause_action->setVisible(false);
  m_stop_action->setEnabled(false);
  m_fullscreen_action->setEnabled(false);
  m_screenshot_action->setEnabled(false);
}

void ToolBar::MakeActions()
{
  constexpr int button_width = 65;
  m_open_action = addAction(tr("Open"), this, SIGNAL(OpenPressed()));
  widgetForAction(m_open_action)->setMinimumWidth(button_width);

  m_play_action = addAction(tr("Play"), this, SIGNAL(PlayPressed()));
  widgetForAction(m_play_action)->setMinimumWidth(button_width);

  m_pause_action = addAction(tr("Pause"), this, SIGNAL(PausePressed()));
  widgetForAction(m_pause_action)->setMinimumWidth(button_width);

  m_stop_action = addAction(tr("Stop"), this, SIGNAL(StopPressed()));
  widgetForAction(m_stop_action)->setMinimumWidth(button_width);

  m_fullscreen_action = addAction(tr("Full Screen"), this, SIGNAL(FullScreenPressed()));
  widgetForAction(m_fullscreen_action)->setMinimumWidth(button_width);

  m_screenshot_action = addAction(tr("Screen Shot"), this, SIGNAL(ScreenShotPressed()));
  widgetForAction(m_screenshot_action)->setMinimumWidth(button_width);

  addSeparator();

  m_paths_action = addAction(tr("Paths"), this, SIGNAL(PathsPressed()));
  widgetForAction(m_paths_action)->setMinimumWidth(button_width);

  m_config_action = addAction(tr("Settings"), this, SIGNAL(SettingsPressed()));
  widgetForAction(m_config_action)->setMinimumWidth(button_width);

  m_controllers_action = addAction(tr("Controllers"));
  widgetForAction(m_controllers_action)->setMinimumWidth(button_width);
  m_controllers_action->setEnabled(false);
}

void ToolBar::UpdateIcons()
{
  QString dir = Settings().GetThemeDir();

  m_open_action->setIcon(QIcon(QStringLiteral("open.png").prepend(dir)));
  m_paths_action->setIcon(QIcon(QStringLiteral("browse.png").prepend(dir)));
  m_play_action->setIcon(QIcon(QStringLiteral("play.png").prepend(dir)));
  m_pause_action->setIcon(QIcon(QStringLiteral("pause.png").prepend(dir)));
  m_stop_action->setIcon(QIcon(QStringLiteral("stop.png").prepend(dir)));
  m_fullscreen_action->setIcon(QIcon(QStringLiteral("fullscreen.png").prepend(dir)));
  m_screenshot_action->setIcon(QIcon(QStringLiteral("screenshot.png").prepend(dir)));
  m_config_action->setIcon(QIcon(QStringLiteral("config.png").prepend(dir)));
  m_controllers_action->setIcon(QIcon(QStringLiteral("classic.png").prepend(dir)));
}
