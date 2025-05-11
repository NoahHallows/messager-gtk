/* quackmessage-application.c
 *
 * Copyright 2025 Noah Hallows
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"
#include <glib/gi18n.h>

#include "quackmessage-application.h"
#include "quackmessage-window.h"

struct _QuackmessageApplication
{
	AdwApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (QuackmessageApplication, quackmessage_application, ADW_TYPE_APPLICATION)

QuackmessageApplication *
quackmessage_application_new (const char        *application_id,
                              GApplicationFlags  flags)
{
	g_return_val_if_fail (application_id != NULL, NULL);

	return g_object_new (QUACKMESSAGE_TYPE_APPLICATION,
	                     "application-id", application_id,
	                     "flags", flags,
	                     "resource-base-path", "/com/quackmail/message",
	                     NULL);
}

static void
quackmessage_application_activate (GApplication *app)
{
	GtkWindow *window;

	g_assert (QUACKMESSAGE_IS_APPLICATION (app));

	window = gtk_application_get_active_window (GTK_APPLICATION (app));

	if (window == NULL)
		window = g_object_new (QUACKMESSAGE_TYPE_WINDOW,
		                       "application", app,
		                       NULL);

	gtk_window_present (window);
}

static void
quackmessage_application_class_init (QuackmessageApplicationClass *klass)
{
	GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

	app_class->activate = quackmessage_application_activate;
}

static void
quackmessage_application_about_action (GSimpleAction *action,
                                       GVariant      *parameter,
                                       gpointer       user_data)
{
	static const char *developers[] = {"Noah Hallows", NULL};
	QuackmessageApplication *self = user_data;
	GtkWindow *window = NULL;

	g_assert (QUACKMESSAGE_IS_APPLICATION (self));

	window = gtk_application_get_active_window (GTK_APPLICATION (self));

	adw_show_about_dialog (GTK_WIDGET (window),
	                       "application-name", "quackmessage",
	                       "application-icon", "com.quackmail.message",
	                       "developer-name", "Noah Hallows",
	                       "translator-credits", _("translator-credits"),
	                       "version", "0.1.0",
	                       "developers", developers,
	                       "copyright", "© 2025 Noah Hallows",
	                       NULL);
}

static void
quackmessage_application_quit_action (GSimpleAction *action,
                                      GVariant      *parameter,
                                      gpointer       user_data)
{
	QuackmessageApplication *self = user_data;

	g_assert (QUACKMESSAGE_IS_APPLICATION (self));

	g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
	{ "quit", quackmessage_application_quit_action },
	{ "about", quackmessage_application_about_action },
};

static void
quackmessage_application_init (QuackmessageApplication *self)
{
	g_action_map_add_action_entries (G_ACTION_MAP (self),
	                                 app_actions,
	                                 G_N_ELEMENTS (app_actions),
	                                 self);
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "app.quit",
	                                       (const char *[]) { "<primary>q", NULL });
}
